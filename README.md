# ATM Management System (C)

A simple ATM/bank system you run in the terminal. You can register or
log in, open accounts, check balances, deposit/withdraw money, update
your info, close an account, or hand an account over to someone else.
As a bonus, if two people are logged in at the same time and one
transfers an account to the other, the other person gets notified
instantly.

## How to run it

```
make        # builds the program
make run    # builds it (if needed) and starts it
```

That's it — follow the prompts on screen.

Want to run the tests instead?

```
make test
```

(On Linux this links against `libcrypt` for password hashing. On a Mac
you don't need it, and the Makefile figures that out on its own.)

## How the code is organized

Instead of one giant file, the program is split into small files that
each do one thing. That makes it much easier to find what you're
looking for and to change one part without breaking another.

| File | What it's responsible for |
|---|---|
| `main.c` | Starting point — shows the login/register screen |
| `menu.c` | The menu you see after logging in |
| `auth.c` | Logging in and registering |
| `crypto.c` | Turning passwords into hashes so they're never stored as plain text |
| `storage.c` | Reading and writing `users.txt` and `records.txt` |
| `accounts.c` | Creating, listing, viewing, and updating accounts |
| `transactions.c` | Deposits and withdrawals |
| `ownership.c` | Deleting an account, or transferring it to someone else |
| `notify.c` | The bonus: instant notification when you receive an account |
| `interest.c` | Just the interest-rate math, kept separate so it's easy to test |
| `ui.c` | Helpers for safely reading what the user types |

The idea: if you ever want to change how data is stored (say, switch
from text files to a real database), you only touch `storage.c` —
nothing else needs to know or care.

## What was broken in the original code, and how it got fixed

- `saveAccountToFile` didn't even compile — it had a typo and mixed up
  pointers and regular variables. Rewritten from scratch.
- Passwords were being read from the wrong columns in `users.txt`,
  which meant logins would basically never work correctly. Fixed by
  reading the file properly.
- User input was read in an unsafe way that could overflow memory if
  someone typed too much. Now every input goes through a safety check.
- Passwords were stored as plain text in the file. Now they're hashed,
  so even if someone opened the file, they wouldn't see the actual
  password.

## What's done

- Login & register (no two users can have the same name)
- Create a new account
- Update your country or phone number
- View one account's details, including how much interest it earns
  (savings 7%, fixed01 4%, fixed02 5%, fixed03 8%, current accounts get none)
- List everything you own
- Deposit or withdraw money (fixed-term accounts can't do this)
- Delete an account
- Transfer an account to someone else
- **Bonus:** the other person gets notified the instant it happens, if
  they're logged in at that moment

## A couple of honest notes

- Data is stored in plain text files and loaded into memory each time,
  which is simple and totally fine for a project like this — just not
  how you'd do it for a real bank with millions of users (that's what
  a real database is for).
- Passwords are hashed properly, but this still isn't "bank-grade"
  security — just solid practice for a school project.
- The interest math lives in its own file with no dependencies on
  files or the terminal, purely so it can be tested on its own. Run
  `make test` to see it checked against the exact example from the
  project instructions.
