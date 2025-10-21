{ pkgs ? import <nixpkgs> {},... }:
with pkgs; 
pkgs.mkShell rec {
    inputsFrom = import ./default.nix pkgs;
}