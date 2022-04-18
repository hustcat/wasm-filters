## example

```
# kubectl -n mesh-app exec -it deploy/sleep -- curl -v -s http://productpage:9080 -o /dev/null
Defaulting container name to sleep.
Use 'kubectl describe pod/sleep-74b7c4c84c-c5xp7 -n mesh-app' to see all of the containers in this pod.
*   Trying 172.17.254.82:9080...
* Connected to productpage (172.17.254.82) port 9080 (#0)
> GET / HTTP/1.1
> Host: productpage:9080
> User-Agent: curl/7.81.0-DEV
> Accept: */*
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< server: envoy
< date: Mon, 18 Apr 2022 06:33:21 GMT
< x-envoy-upstream-service-time: 3
< header-added-by: dbyin
< content-type: text/plain; charset=utf-8
< transfer-encoding: chunked
< 
{ [1695 bytes data]
* Connection #0 to host productpage left intact
```
