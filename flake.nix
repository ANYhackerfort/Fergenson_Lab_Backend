{
  description = "Backend for lab";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    devenv.url = "github:cachix/devenv";
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [
        inputs.devenv.flakeModule
      ];

      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "aarch64-darwin"
        "x86_64-darwin"
      ];

      perSystem =
        {
          pkgs,
          config,
          ...
        }:
        {
          packages.default = pkgs.callPackage ./nix { };
          formatter = pkgs.nixfmt-rfc-style;

          # the development environment for this project
          # provides `cmake`, `clang`, `clangd`, and all required dependencies (boost, opencv, libtorch)
          devenv.shells.default =
            let
              inherit (pkgs) libtorch-bin boost opencv;
            in
            {
              enterShell = ''
                export CWD=$(pwd)
              '';
              stdenv = pkgs.llvmPackages_19.stdenv;
              packages =
                [
                  config.packages.default
                  libtorch-bin
                  boost
                  opencv
                ]
                ++ (with pkgs; [
                  cmake
                ]);

              languages.cplusplus.enable = true;

              scripts = {
                format.exec = ''
                  find $CWD/{src,include} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
                '';
                lint.exec = ''
                  find $CWD/{src,include} -name '*.cpp' -o -name '*.h' \
                    | xargs -I{} clang-tidy -p=./compile_commands.json -checks='*' {}
                '';
                build.exec = ''
                  cmake .
                  make
                '';
                setup-clangd.exec = ''
                  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
                '';
              };

              git-hooks = {
                clang-format.enable = true;
                clang-tidy.enable = true;
                shellcheck.enable = true;
              };
            };
        };
    };
}
