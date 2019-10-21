FROM alpine:latest AS builder
WORKDIR /root/build
RUN apk --no-cache add g++
COPY cpuhog.cpp .
RUN g++ -O2 -static -o cpuhog cpuhog.cpp

FROM scratch
WORKDIR /root/
COPY --from=builder /root/build/cpuhog .
CMD ["./cpuhog"]  
