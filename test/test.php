<?php
/**
 * All rights reserved. No part of this code may be reproduced, modified,
 * amended or retransmitted in any form or by any means for any purpose without
 * prior written consent of Mizmoz Limited.
 * You must ensure that this copyright notice remains intact at all times
 *
 * @package Mizmoz
 * @copyright Copyright (c) Mizmoz Limited 2016. All rights reserved.
 */

$message = file_get_contents('bounce-example.txt');
$license = "Test User/123456789";

$bounceStudio = new BounceStudio($license, $message);

$methods = [
    [
        'method' => 'getBounceCode',
        'args' => [],
    ],
    [
        'method' => 'getBounceEmail',
        'args' => [],
    ],
    [
        'method' => 'getBody',
        'args' => [],
    ],
    [
        'method' => 'getHeader',
        'args' => ['date'],
    ],
    [
        'method' => 'getOriginalHeader',
        'args' => ['message-id'],
    ],
    [
        'method' => 'getFromAddress',
        'args' => [],
    ],
    [
        'method' => 'getFromName',
        'args' => [],
    ],
    [
        'method' => 'getToAddress',
        'args' => [],
    ],
    [
        'method' => 'getToName',
        'args' => [],
    ],
    [
        'method' => 'getReplyToAddress',
        'args' => [],
    ],
    [
        'method' => 'getReplyToName',
        'args' => [],
    ],
    [
        'method' => 'getSubject',
        'args' => [],
    ],
    [
        'method' => 'getHeaders',
        'args' => [],
    ],
];

/**
 * Increase the iterations for memory checking
 */
for ($i = 0; $i < 1; $i++) {
    for ($j = 0; $j < 1; $j++) {
        foreach ($methods as $method) {
            $result = call_user_func_array([$bounceStudio, $method['method']], $method['args']);

            echo 'method: $bounceStudio->' . $method['method'] .
                "(" . (count($method['args']) ? join(", ", $method['args']) : '') . ");\n";
            echo 'result: ' . $result . "\n\n";
            echo str_pad('', 80, '#') . "\n\n";
        }
    }

    echo number_format(memory_get_usage(true)) . "\n";
}
