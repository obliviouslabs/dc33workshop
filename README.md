This repo contains the handout for two sample ctf style problems for the dc33 workshop.

The goal of the programs challenges to show the kind of information that can be retrieved from encrypted memory traces or from instruction traces.

Once you solve the problem, please upload the flag here: https://forms.gle/YTXrRd2ApESdHene8

# Problem 1 - Password check program

- Compares user input against flag

- `client.py` contains sample client, it connects to ws.xtrm0.com:4333 (you can also use `nc ws.xtrm0.com 4333`)

- You are given encrypted memory after each instruction

- Recover the flag


# Problem 2 - Sorts user input

- Uses bitonic sort to sort the flag

- You are given the sorted flag and information about which branches were taken (`instruction_trace.txt`)

- Recover the original flag
