# 使用輕量級的編譯環境
FROM gcc:12.2.0-bookworm as builder
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN g++ -o myapp main.cpp

# 執行階段使用更小的 Image 以優化速度與安全
FROM debian:bookworm-slim
WORKDIR /root/
COPY --from=builder /usr/src/myapp/myapp .
CMD ["./myapp"]