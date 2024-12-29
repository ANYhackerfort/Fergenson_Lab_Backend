{
  cmake,
  libtorch-bin,
  boost,
  opencv,
  meson,
  ninja,
  pkg-config,
  llvmPackages_19,
  grpc,
  callPackage,
  lib,
}:
let
  protobuf = callPackage ./protobuf_29_2.nix { };
in
llvmPackages_19.stdenv.mkDerivation (finalAttrs: {
  pname = "WebSocketWithOpenCV";
  version = "0.1.0";

  src = ../.;

  nativeBuildInputs = [
    meson
    ninja
    cmake
    pkg-config
  ];

  buildInputs = [
    boost
    opencv
    libtorch-bin
    grpc
    protobuf
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp WebSocketWithOpenCV $out/bin
  '';

  meta = {
    maintainers = [ lib.maintainers.youwen5 ];
    mainProgram = "WebSocketWithOpenCV";
  };
})
