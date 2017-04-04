These services/scripts enables the raspberry to launch the emergent_robot application at launch
It does this through the provided systemd service configurations
Place .service files in /lib/systemd/system/
This includes waiting for the thymio-connection service to launch first,
followed by the boot-pi-camera that modprobes the camera so the system can access it