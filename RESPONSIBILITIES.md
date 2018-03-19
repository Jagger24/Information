Responsibilities of Each Person:
Cat:
- Hashing algorithm with customizable length
  > will allow us to create:
    - 6 & 9 character code
Abdi:
- get input of random hash from users from Ruby on Rails @ Login & @ Password Forget
- let the user know if the code matches their account
Evan:
- create encryption & decryption algorithm to protect all hash codes safe in database
Rebecca:
- coding the SMS that sends the 6 & 9-character codes
Jeff:
- create all functions/interface of the website/controller & database methods for each part of the process

====
Details of Project:
> 6-Character Code = sent to user for all subsequent login's after the user signs up (no 6-char code sent at sign-up)
  - 1 code will be sent at login, 1-time use
> 9-character code = sent to user ONLY when user signs up
  - user will be responsible to save this code to use when they forget their password
  - 1 code will be sent at sign up, 1-time use, then a new one will have to be sent when user uses it to login without password
