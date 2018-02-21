#include <stdio.h>
#include <time.h>
#include <iwlib.h>

int main(void) {
  wireless_scan_head head;
  wireless_scan *result;
  iwrange range;
  int sock;

  /* Open socket to kernel */
  sock = iw_sockets_open();

  /* Get some metadata to use for scanning */
  if (iw_get_range_info(sock, "wlp1s0", &range) < 0) {
    printf("Error during iw_get_range_info. Aborting.\n");
    exit(2);
  }

  /* Perform the scan */
  if (iw_scan(sock, "wlp1s0", range.we_version_compiled, &head) < 0) {
    printf("Error during iw_scan. Aborting.\n");
    exit(2);
  }

  /* Traverse the results */
  result = head.result;
  int nameless_networks = 0;
  while (NULL != result) {
    if(strlen(result->b.essid)) {
        printf("%s\n", result->b.essid);
    } else {
        nameless_networks ++;
    }
    result = result->next;
  }

  if(nameless_networks) {
    printf("%d networks with no essid were found. Run iwlist to list all available networks.\n", nameless_networks);
  }
    

  exit(0);
}
