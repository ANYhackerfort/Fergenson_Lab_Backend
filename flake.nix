{
  description = "Backend for lab";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    devenv.url = "github:cachix/devenv";
    devenv.inputs.nixpkgs.follows = "nixpkgs";
    nix2container.url = "github:nlewo/nix2container";
    nix2container.inputs.nixpkgs.follows = "nixpkgs";
    mk-shell-bin.url = "github:rrbutani/nix-mk-shell-bin";
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
        let
          clang-tools = pkgs.llvmPackages_19.clang-tools;
        in
        {
          packages = {
            default = pkgs.callPackage ./nix { };
          };
          formatter = pkgs.treefmt;

          # the development environment for this project
          # provides `cmake`, `clang`, `clangd`, and all required dependencies (boost, opencv, libtorch)
          devenv.shells.default = {
            enterShell = ''
              export CWD=$(pwd)
            '';
            stdenv = pkgs.llvmPackages_19.stdenv;
            packages =
              [
                pkgs.mesonlsp
                clang-tools
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
              shellcheck.enable = true;
              treefmt.enable = true;
              treefmt.settings.formatters = [
                pkgs.nixfmt-rfc-style
                clang-tools
                pkgs.taplo
                pkgs.meson
                pkgs.nodePackages_latest.prettier
              ];
            };

          };
        };
    };

  nixConfig = {
    extra-trusted-public-keys = "devenv.cachix.org-1:w1cLUi8dv3hnoSPGAuibQv+f9TZLr6cv/Hm9XgU50cw=";
    extra-substituters = "https://devenv.cachix.org";
  };
}
