FROM ubuntu:24.04

RUN apt clean && apt autoclean
RUN apt update && apt -yqq upgrade
RUN apt install -yqq gcc make libssl-dev coreutils
RUN apt install -yqq socat ncat 
RUN apt-get autoremove -yqq
RUN apt-get clean 
RUN rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get -yqq upgrade
RUN apt-get install -yqq socat
RUN apt-get autoremove -yqq && apt-get clean && rm -rf /var/lib/apt/lists/* 

RUN adduser --disabled-password --gecos '' ctf
USER ctf

WORKDIR /home/ctf

COPY --chown=ctf encrypted_memory_interactive.elf /home/ctf/
COPY --chown=ctf flag_interactive.txt /home/ctf/

RUN chmod +x /home/ctf/encrypted_memory_interactive.elf 

EXPOSE 4333

CMD ["socat", "-T300", "TCP-LISTEN:4333,reuseaddr,fork", "EXEC:/home/ctf/encrypted_memory_interactive.elf"]
# CMD ["ncat", "-l", "4333", "-c", "/home/ctf/encrypted_memory_interactive.elf", "--keep-open"]
# CMD ["nc", "-lvkp", "4333", "-e", "/home/ctf/encrypted_memory_interactive.elf"]
