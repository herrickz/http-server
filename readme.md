

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