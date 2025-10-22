{config,lib, pkgs,...}: 
let
  cfg = config.services.hidrosis;
  hidrosis = pkgs.callPackage ./default.nix {inherit pkgs; };
in
{
    options.services.hidrosis = {
        enable = lib.mkEnableOption "Enable hidrosis service and udev rule";
    };

    config = lib.mkIf cfg.enable {
        services.udev.packages = [ hidrosis ];

        systemd.user.services."hidrosis.service" = {
            text = builtins.readFile ./hidrosis/packaging/linux/systemd/hidrosis.service;
        };
        
        environment.systemPackages = [ hidrosis ];
    };
}