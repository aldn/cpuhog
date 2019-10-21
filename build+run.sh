docker build -t cpuhog:latest .
docker container run -d --name cpuhog --cpuset-cpus=4,5,6,7 cpuhog:latest
