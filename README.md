# udp_average_tracker
Write a Linux C++ application that performs the following:

1. UDP server that receives messages from a client. Each message consists of a single 32-bit value. The client will send the value at a random interval but at a rate no faster than 1 per second and no slower than 1 per minute.

2. The application should persist the received values in a DB (SQLite for example) along with a timestamp of when it was received.

3. The application should compute the average of the received values every 5 minutes. After a 5-minute interval, a new average will be computed. The 5-minute averages should be store inside the DB as well.
