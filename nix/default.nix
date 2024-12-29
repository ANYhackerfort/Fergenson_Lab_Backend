{
  cmake,
  libtorch-bin,
  boost,
  opencv,
  meson,
  ninja,
  pkg-config,
  llvmPackages_19,
  callPackage,
  lib,
}:
let
  protobuf = callPackage ./protobuf_29_2.nix { inherit grpc; };
  grpc = callPackage ./grpc.nix { inherit protobuf; };
in
llvmPackages_19.stdenv.mkDerivation {
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
    install -Dm755 WebSocketWithOpenCV $out/bin/WebSocketWithOpenCV
  '';

  meta = {
    maintainers = [ lib.maintainers.youwen5 ];
    mainProgram = "WebSocketWithOpenCV";
  };
}
