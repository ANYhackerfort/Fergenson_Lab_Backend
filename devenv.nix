{ pkgs, config }:
let
  clang-tools = pkgs.llvmPackages_19.clang-tools;
in
{
  stdenv = pkgs.llvmPackages_19.stdenv;
  packages =
    [
      pkgs.mesonlsp
      clang-tools
    ]
    ++ config.packages.default.buildInputs
    ++ config.packages.default.nativeBuildInputs;

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

  starship.enable = true;
}
