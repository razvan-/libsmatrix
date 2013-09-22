// This file is part of the "recommendify" project
//   (c) 2011-2013 Paul Asmuth <paul@paulasmuth.com>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include "smatrix.h"

smatrix_t* db;

int main(int argc, char **argv) {
  db = smatrix_open("/var/tmp/reco.db");

  if (db == NULL)
    abort();

  smatrix_update(db, 42, 17);
  smatrix_update(db, 42, 17);
  smatrix_gc(db);
  smatrix_update(db, 42, 17);
  smatrix_sync(db);
  exit(0);

  uint64_t i, n;

  for (n = 23; n < 1000; n++) {
    for (i = 0; i < 1000; i++) {
      smatrix_update(db, n, i);
    }

    smatrix_sync(db);
  }

  exit(0);

  smatrix_close(db);
  return 0;
}
