# syntax=docker/dockerfile:1

########## Build stage (Alpine + musl, static binary) ##########
FROM alpine:3.19 AS build
RUN apk add --no-cache build-base musl-dev file
WORKDIR /src
COPY sleepx.c .

# Create output directory, compile static, strip symbols, show file info
RUN mkdir -p /out \
 && gcc -Os -static -s -o /out/sleepx sleepx.c \
 && file /out/sleepx

########## Final stage (true scratch) ##########
FROM scratch
# Run as non-root (65532 = "nobody" in many distros)
USER 65532:65532
COPY --from=build /out/sleepx /sleepx
ENTRYPOINT ["/sleepx"]
# Default: sleep indefinitely; you can override with an integer (seconds)