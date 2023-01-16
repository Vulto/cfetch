#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char host[64];
		char os[] = "Gentoo Linux", kernel[64], uptime[64], shell[16], ui[64], uitype[8];
    int packages;
    FILE* file;
    char buffer[64], command[64];

    // Get hostname
 		gethostname(host, sizeof host);

    // Get kernel version
    file = popen("uname -sr", "r");
    fgets(kernel, sizeof kernel, file);
    pclose(file);

    // Get uptime
    file = popen("uptime -p | sed 's/up //'", "r");
    fgets(uptime, sizeof uptime, file);
    pclose(file);

    // Get number of packages
    file = popen("pacman -Qqen | wc -l", "r");
    fgets(buffer, sizeof buffer, file);
    sscanf(buffer, "%d", &packages);
    pclose(file);

    // Get shell
    sprintf(command, "basename $SHELL");
    file = popen(command, "r");
    fgets(shell, sizeof shell, file);
    pclose(file);

    // Get UI
    if (getenv("DE")) {
        strcpy(ui, getenv("DE"));
        strcpy(uitype, "DE");
    } else if (getenv("WM")) {
        strcpy(ui, getenv("WM"));
        strcpy(uitype, "WM");
    } else if (getenv("XDG_CURRENT_DESKTOP")) {
        strcpy(ui, getenv("XDG_CURRENT_DESKTOP"));
        strcpy(uitype, "DE");
    } else if (getenv("DESKTOP_SESSION")) {
        strcpy(ui, getenv("DESKTOP_SESSION"));
        strcpy(uitype, "DE");
    } else {
        strcpy(ui, "unknown");
        strcpy(uitype, "UI");
    }

    //remove new line characters
    for (int i = 0; i < strlen(kernel); i++) {
        if (kernel[i] == '\n') {
            kernel[i] = '\0';
        }
    }

    for (int i = 0; i < strlen(uptime); i++) {
        if (uptime[i] == '\n') {
            uptime[i] = '\0';
        }
    }

    for (int i = 0; i < strlen(shell); i++) {
        if (shell[i] == '\n') {
            shell[i] = '\0';
        }
    }

    for (int i = 0; i < strlen(ui); i++) {
        if (ui[i] == '\n') {
            ui[i] = '\0';
        }
    }
    printf("\n\
    .-----.      %s@%s\n\
  .`    _  `.    OS:        %s\n\
  `.   (_)   `.  KERNEL:    %s\n\
    `.       .`  UPTIME:    %s\n\
   .`       .`   PACKAGES:  %d\n\
  /       .`     SHELL:     %s\n\
  ____.-`       %s:        %s\n\n", getenv("USER"), host, os, kernel, uptime, packages, shell, uitype, ui);
    return 0;
}

