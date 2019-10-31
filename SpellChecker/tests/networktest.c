/*
 * Slightly modified Tiny Web Server from Bryant & O'Hallaron
 * Does not serve content to the client, but the server receives information
 * about the conneceted client
 */

#include "../csapp.h"

void doWork(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void get_filetype(char *filename, char *filetype);

int main(int argc, char **argv) {
  int listenfd, connfd, port, clientlen;
  struct sockaddr_in clientaddr;

  // Check args
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>", argv[0]);
    exit(1);
  }

  // Set port
  port = atoi(argv[1]);

  listenfd = open_listenfd(port);

  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (SA *)&clientaddr, (socklen_t *)&clientlen);
    doWork(connfd);
    close(connfd);
  }
}

// doit method from B&O'H
void doWork(int fd) {
  int isStatic;
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE],
      filename[MAXLINE], cgiargs[MAXLINE];
  rio_t rio;

  // Read request line and headers
  rio_readinitb(&rio, fd);
  rio_readlineb(&rio, buf, MAXLINE);
  sscanf(buf, "%s %s %s", method, uri, version);
  if (strcasecmp(method, "GET")) {
    return;
  }
  read_requesthdrs(&rio);

  // Parse URI from GET request
  isStatic = parse_uri(uri, filename, cgiargs);
  if (stat(filename, &sbuf) < 0) {
    return;
  }

  if (isStatic) {  // Serve static content
    if (!(S_ISREG(sbuf.st_mode) || !(S_IRUSR & sbuf.st_mode))) {
      return;
    }
    serve_static(fd, filename, sbuf.st_size);
  } else {  // Serve dynamic content
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
      return;
    }
    serve_dynamic(fd, filename, cgiargs);
  }
}

// Reads and ignores request headers
void read_requesthdrs(rio_t *rp) {
  char buf[MAXLINE];

  do {
    rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
  } while (strcmp(buf, "\r\n"));
  return;
}

int parse_uri(char *uri, char *filename, char *cgiargs) {
  char *ptr;

  if (!strstr(uri, "cgi-bin")) { /* Static content */
    strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    if (uri[strlen(uri) - 1] == '/') strcat(filename, "home.html");
    return 1;
  } else { /* Dynamic content */
    ptr = index(uri, '?');
    if (ptr) {
      strcpy(cgiargs, ptr + 1);
      *ptr = '\0';
    } else
      strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    return 0;
  }
}

void serve_static(int fd, char *filename, int filesize) {
  int srcfd;
  char *srcp, filetype[MAXLINE], buf[MAXLINE];

  get_filetype(filename, filetype);
}

void serve_dynamic(int fd, char *filename, char *cgiargs) {
  //
}

void get_filetype(char *filename, char *filetype) {
  //
}