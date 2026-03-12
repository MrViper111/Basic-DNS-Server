# Basic "DNS" Server
This is technically not an actual DNS server since it does not use the same protocol but it performs essentially the same task. Both the client and the server are provided as well as a script (`get_addr.c`) to convert an IPv4 string to the proper network order address, a `uint32_t`.

## Commands (client)
* `get <domain>` - returns the IPv4 of a domain listed in `data.txt`. If it is not already cached, it will request it from the server. If it already cached, it will use whatever is stored in `cache.txt`.
* `put <domain:address` - sends a request to the server to add the new record to `data.txt`. Note `address` must be an integer which you can get using the `get_addr.c` script.
* `clearcache` - deletes all content in `cache.txt`.

**Note:** Other than checking a few things, the server will not care if you pass in any malformed inputs so make sure you are entering the commands correctly.

## Fun Features (to add later perhaps)
* `list` command which gets the contents of `data.txt` from the server.
* Have clients authenticate or identify themselves upon connecting (security).
* A possible rate limit for clients.
