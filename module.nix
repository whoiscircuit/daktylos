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

        systemd.user.units."hidrosis.service" = 
        let 
            originalServiceText = builtins.readFile ./hidrosis/packaging/linux/systemd/hidrosis.service;
            serviceWithInjectedExecutablePath = builtins.replaceStrings ["/usr/bin/hidrosis"] ["${hidrosis}/bin/hidrosis"] originalServiceText;
        in {
            text = serviceWithInjectedExecutablePath;
        };
        
        environment.systemPackages = [ hidrosis ];
    };
}