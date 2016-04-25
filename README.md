# PHP 7 Module for Boogie Tools - BounceStudio 

BounceStudio by Boogie Tools is a paid for library for handling your bounce emails - see http://www.boogietools.com/ for more details.

PHP module code provided by Mizmoz under the MIT license - https://www.mizmoz.com/

## Building

In the src/ directory run:

```
phpize7.0

./configure --enable-bouncestudio

make CFLAGS="-lBounceStudio64 $CFLAGS"

make install

```

Find your PHP conf directory

```php -i|grep "^Scan this dir for additional .*$"|grep -oh '/etc.*$'```

Create the ini file

```echo 'extension=bouncestudio.so' > /path/to/modules/20-bouncestudio.ini```

## Usage

```php
$license = "Test User/123456789";
$message = "Date: Fri, 14 Nov 2003 14:00:01 -0500
Message-ID: <AauNjVuMhvq0000007c@elsewhere.com>
From: \"Mr. PostMaster\" <postmaster@elsewhere.com>
Reply-To: \"My Reply Account\" <postmaster_reply@elsewhere.com>
Subject: Failure Notice
To: \"Mrs. Someone\" <someone@somewhere.com>

Hi. This is the mail transport agent at mail.elsewhere.com.
I'm afraid I wasn't able to deliver your message to the
following addresses.  This is a permanent error; I've
given up. If you have questions about this notice, please
forward it to postmaster@elsewhere.com along with your
comments.

<john@smith.com>:
Sorry, this account has been deactivated. (#5.2.1)

--- Below this line is a copy of the message.

Return-Path: <someone@somewhere.com>

From: \"Mrs. Someone\" <someone@somewhere.com>
Reply-To: \"Mrs. Someone\" <someone_reply@somewhere.com>
To: \"John Smith\" <dave@smith.com>
Date: Mon, 21 Aug 00 13:50:20 -0700
Subject: JOE.NET NEWS!
MIME-Version: 1.0
Message-ID: <agW2wx6Di110f7@somewhere.com>

This is a multi-part message in MIME format.

etc.
etc.
etc..";
$ignoreAddresses = 'noreply@mizmoz.net|you@example.com';

$bounceStudio = new BounceStudio($license, $message, $ignoreAddresses);

// Get the bounce code
// @see http://www.boogietools.com/Products/Linux/BounceStudioAPI/Email-Bounce-Boogie-Bounce-API-Categories.asp
$code = $bounceStudio->getBounceCode();

// Get the bounced email address
$bounceEmail = $bounceStudio->getBounceEmail();

// Get the message body
$body = $bounceStudio->getBody();

// Get the email headers as a string
$headers = $bounceStudio->getHeaders();

// Get a specific header from the bounce email
$date = $bounceStudio->getHeader('date');

// Get a specific header from the original email
$messageId = $bounceStudio->getOriginalHeader('message-id');

// Get the from email address
$fromEmail = $bounceStudio->getFromAddress();

// Get the from name
$fromName = $bounceStudio->getFromName();

// Get the to email address
$toEmail = $bounceStudio->getToAddress();

// Get the to name
$toName = $bounceStudio->getToName();

// Get the reply-to email address
$replyToEmail = $bounceStudio->getReplyToAddress();

// Get the reply-to name
$replyToName = $bounceStudio->getReplyToName();

// Get the subject
$subject = $bounceStudio->getSubject();
```
