
# HTTP Server

Implementation of an HTTP server

## Roadmap

- [ ] Serve HTML files from a directory
- [ ] Default values for command line argument parser
- [ ] Add positional parameters to command line argument parser

## Done

- [x] Command line argument parser
  - Port to run on
  - Directory to serve files from

## Building

```shell
./run.sh -d # Debug (Default)
./run.sh -r # Release
./run.sh -c # Clean
./run.sh -t # Test
```

## Testing

```shell
curl --header "Content-Type: application/json" \
  --request POST \
  --data '@large.json' \
  http://127.0.0.1:9090
```