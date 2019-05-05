Clean Code
----------
Write a function that will receive the log, i.e. a sequence of timestamps in chronological order. Each timestamp denotes single time the user has opened the website. The function should return True if we should ask the user for his or her opinion and False otherwise. Timestamps are strings in the format of 'YYY-MM-DD hh:mm:ss', using user's time zone. You can assume that the last entry is with today's date.
Please try to write code that is very readable and maintainable.

Example:
--------
--------
['2017-03-10 08:13:11', '2017-03-10 19:01:27', '2017-03-11 07:35:55', '2017-03-11 16:15:11', '2017-03-12 08:01:41', '2017-03-12 17:19:08']
Result: True (6 sessions during over 3 days)