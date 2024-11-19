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

              enterShell = ''
                export CMAKE_PREFIX_PATH=${libtorch-bin}:${boost}:${opencv}:$CMAKE_PREFIX_PATH
              '';

              languages.cplusplus.enable = true;
            };
        };
    };
}
