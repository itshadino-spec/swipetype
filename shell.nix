{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    pkg-config
  ];

  buildInputs = with pkgs; [
    SDL2
    SDL2_image
  ];
}
