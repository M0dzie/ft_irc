# ft_irc

## How IRC should work
<div>
	<img src="https://media.geeksforgeeks.org/wp-content/uploads/20220330131350/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png">
	<img src="https://raw.githubusercontent.com/marineks/Ft_irc/main/assets/irc-shema.png">
</div>

## IRC behaviour
### Channels
- A channel is a named group of one or more clients. All clients in the channel will receive all messages addressed to that channel. The channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it. 
- Channel names are string which first character is `#`, and the only restriction on a channel name is that it may not contain any spaces (' ', 0x20), a control G / BELL ('^G', 0x07), or a comma (',', 0x2C) (which is used as a list item separator by the protocol).
- To create a new channel or become part of an existing channel, a user is required to join the channel using the `JOIN` command. If the channel doesn’t exist prior to joining, the channel is created and the creating user becomes a channel operator.
- For example, if the channel is set to `invite-only mode (+i)`, the client only joins the channel if they have been invited by another user or they have been exempted from requiring an invite by the channel operators.
- Channels also contain a topic. The topic is a line shown to all users when they join the channel, and all users in the channel are notified when the topic of a channel is changed.
- A user may be joined to several channels at once, but a limit may be imposed by the server as to how many channels a client can be in at one time. This limit is specified by the CHANLIMIT RPL_ISUPPORT parameter.

### Channel Operators
- Channel operators (or “chanops”) on a given channel are considered to ‘run’ or ‘own’ that channel.
- The commands which may only be used by channel moderators include:
	1. `KICK`: Eject a client from the channel
	2. `MODE`: Change the channel’s modes
	3. `INVITE`: Invite a client to an invite-only channel (mode +i)
	4. `TOPIC`: Change the channel topic in a mode +t channel
- Channel moderators are identified by the channel member prefix `@` for standard channel operators

### Message Format
- An IRC message is a single line, delimited by a pair of `\r` and `\n` characters.
	1. When reading messages from a stream, read the incoming data into a buffer. Only parse and process a message once you encounter the `\r\n` at the end of it. If you encounter an empty message, silently ignore it.
	2. When sending messages, ensure that a pair of `\r\n` characters follows every single message your software sends out.

### Connection Registration 
- The recommended order of commands during registration is as follows:
	1. `CAP LS 302`
	2. `PASS`
	3. `NICK and USER`
	4. `Capability Negotiation`
	5. `SASL (if negotiated)`
	6. `CAP END`


## Docs
#### Socket explanation
https://www.geeksforgeeks.org/socket-programming-cc/

#### Command handling
https://modern.ircdocs.horse/

### Using Internet Sockets
https://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf