# dockerSleep

A minimal Docker image that does nothing but sleep. Built from `scratch` with a single static C binary, the final image is only a few (~24) kilobytes.

By default the container sleeps forever. You can optionally pass a number of seconds to sleep for a fixed duration.

## Usage

```bash
# Sleep forever
docker run ghcr.io/jdetmold/dockersleep

# Sleep for one hour
docker run ghcr.io/jdetmold/dockersleep 3600
```

## How it works

`sleepx.c` is compiled as a static musl binary and copied into a `scratch` image with no OS, shell, or other tools. It runs as a non-root user (UID 65532).

## Building locally

```bash
docker build -t dockersleep .
```
