#!/usr/bin/env python
import logging
import time

logger = logging.getLogger(__name__)

if "__main__" == __name__:

    start_time = time.time()
    n = 1 << 22
    while 0 < n:
        logger.debug(f"Test debug : {n}")
        n -= 1
    print(f"Time Elapsed: {time.time() - start_time}s")

    start_time = time.time()
    n = 1 << 22
    while 0 < n:
        logger.debug("Test debug : %d", n)
        n -= 1
    print(f"Time Elapsed: {time.time() - start_time}s")

