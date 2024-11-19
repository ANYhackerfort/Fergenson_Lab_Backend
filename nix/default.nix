{
  stdenv,
  cmake,
  libtorch-bin,
  boost,
  opencv,
  lib,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "lab-backend";
  version = "0.1.0";

  src = ../.;

  nativeBuildInputs = [
    cmake
    boost
    opencv
    libtorch-bin
  ];

  cmakeFlags = [
    # provide path to libtorch
    "-DCMAKE_PREFIX_PATH=${libtorch-bin}"
  ];

  buildPhase = ''
    cmake --build .
    make
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp WebSocketWithOpenCV $out/bin
  '';

  meta = {
    maintainers = [ lib.maintainers.youwen5 ];
    mainProgram = "WebSocketWithOpenCV";
  };
})
