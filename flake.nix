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
        "aarch64-darwin"
      ];

      perSystem =
        {
          pkgs,
          config,
          ...
        }:
        {
          packages = {
            default = pkgs.callPackage ./nix { liboai = config.packages.liboai; };
            liboai = pkgs.callPackage ./nix/liboai.nix { };
          };
          formatter = pkgs.nixfmt-rfc-style;

          # the development environment for this project
          # provides `cmake`, `clang`, `clangd`, and all required dependencies (boost, opencv, libtorch)
          devenv.shells.default = {
            enterShell = ''
              export CWD=$(pwd)
            '';
            stdenv = pkgs.llvmPackages_19.stdenv;
            packages =
              with pkgs;
              [
                llvmPackages_19.clang-tools
                mesonlsp
              ]
              ++ config.packages.default.buildInputs
              ++ config.packages.default.nativeBuildInputs;

            scripts = {
              format.exec = ''
                find $CWD/{src,include} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
              '';
              lint.exec = ''
                find $CWD/{src,include} -name '*.cpp' -o -name '*.h' \
                  | xargs -I{} clang-tidy -p=./compile_commands.json -checks='*' {}
              '';
            };

            git-hooks.hooks = {
              clang-format.enable = true;
              shellcheck.enable = true;
              nixfmt-rfc-style.enable = true;
            };
          };
        };
    };
}
