-- Keep a log of any SQL queries you execute as you solve the mystery

-- REVEALING IDENTITY OF THIEF
SELECT name FROM people
WHERE
(
    id IN
    (
        SELECT people.id FROM courthouse_security_logs
        JOIN people ON courthouse_security_logs.license_plate = people.license_plate
        WHERE (month == 7 AND day == 28 AND hour == 10 AND minute >= 15 AND minute <= 25)
    )
    AND
    id IN
    (
        SELECT person_id FROM atm_transactions
        JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
        WHERE (month == 7 AND DAY == 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")
    )
    AND
    id IN
    (
        SELECT people.id FROM phone_calls
        JOIN people ON phone_calls.caller = people.phone_number
        WHERE (month == 7 AND day == 28 AND duration < 60)
    )
    AND
    id IN
    (
        SELECT id FROM passengers
        JOIN people ON passengers.passport_number = people.passport_number
        WHERE flight_id IN
        (
            SELECT id FROM flights
            WHERE (month == 7 AND day == 29)
            AND origin_airport_id IN
            (
                SELECT id FROM airports
                WHERE city == "Fiftyville"
            )
            ORDER BY hour, minute LIMIT 1
        )
    )
);


-- REVEALING CITY THIEF ESCAPED TO
SELECT city FROM airports
WHERE id IN
(
    SELECT destination_airport_id FROM flights
    WHERE (month == 7 AND day == 29)
    AND origin_airport_id IN
    (
        SELECT id FROM airports
        WHERE city == "Fiftyville"
    )
    ORDER BY hour, minute LIMIT 1
);


-- REVEALING ACCOMPLICE OF THIEF
SELECT name FROM people
WHERE phone_number IN
(
    SELECT receiver FROM phone_calls
    WHERE (month == 7 AND day == 28 AND duration < 60)
    AND caller IN
    (
        SELECT phone_number FROM people
        WHERE
        (
            id IN
            (
                SELECT people.id FROM courthouse_security_logs
                JOIN people ON courthouse_security_logs.license_plate = people.license_plate
                WHERE (month == 7 AND day == 28 AND hour == 10 AND minute >= 15 AND minute <= 25)
            )
            AND
            id IN
            (
                SELECT person_id FROM atm_transactions
                JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
                WHERE (month == 7 AND DAY == 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")
            )
            AND
            id IN
            (
                SELECT people.id FROM phone_calls
                JOIN people ON phone_calls.caller = people.phone_number
                WHERE (month == 7 AND day == 28 AND duration < 60)
            )
            AND
            id IN
            (
                SELECT id FROM passengers
                JOIN people ON passengers.passport_number = people.passport_number
                WHERE flight_id IN
                (
                    SELECT id FROM flights
                    WHERE (month == 7 AND day == 29)
                    AND origin_airport_id IN
                    (
                        SELECT id FROM airports
                        WHERE city == "Fiftyville"
                    )
                    ORDER BY hour, minute LIMIT 1
                )
            )
        )
    )
);


-- ARRIVING AT SOLUTION
/*
    SELECT description FROM crime_scene_reports
    WHERE (month == 7 AND day == 28 AND description LIKE "%CS50%");
        Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
        Interviews were conducted today with three witnesses who were present at the time
        — each of their interview transcripts mentions the courthouse.

    SELECT name, transcript FROM interviews
    WHERE (month == 7 AND day == 28 AND transcript LIKE "%courthouse%");
        RUTH :
            Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
            If you have security footage from the courthouse parking lot,
            you might want to look for cars that left the parking lot in that time frame.
        EUGENE :
            I don't know the thief's name, but it was someone I recognized.
            Earlier this morning, before I arrived at the courthouse,
            I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
        RAYMOND :
            As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
            In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
            The thief then asked the person on the other end of the phone to purchase the flight ticket.

    FOLLOWING RUTH'S STATEMENT :
        SELECT license_plate FROM courthouse_security_logs
        WHERE (month == 7 AND day == 28 AND hour == 10 AND minute >= 15 AND minute <= 25);
            5P2BI95
            94KL13X
            6P58WS2
            4328GD8
            G412CB7
            L93JTIZ
            322W7JE
            0NTHK55

    FOLLOWING EUGENE'S STATEMENT :
        SELECT account_number FROM atm_transactions
        WHERE (month == 7 AND DAY == 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
            28500762
            28296815
            76054385
            49610011
            16153065
            25506511
            81061156
            26013199

    FOLLOWING RAYMOND'S STATEMENT :
        SELECT caller, reciever FROM phone_calls
        WHERE (month == 7 AND day == 28 AND duration < 60);
            THIEF(caller)   ACCOMPLICE(reciever)
            (130) 555-0289  (996) 555-8899
            (499) 555-9472  (892) 555-8872
            (367) 555-5533  (375) 555-8161
            (499) 555-9472  (717) 555-1342
            (286) 555-6063	(676) 555-6554
            (770) 555-1861  (725) 555-3243
            (031) 555-6622  (910) 555-3251
            (826) 555-1652  (066) 555-9701
            (338) 555-6650  (704) 555-2131
        SELECT id FROM airports
        WHERE city == "Fiftyville";
            8
        SELECT id, destination_airport_id FROM flights
        WHERE (origin_airport_id == 8 AND month == 7 AND day == 29)
        ORDER BY hour, minute LIMIT 1;
            flight id = 36
            airport id = 4
        SELECT passport_number FROM passengers
        WHERE flight_id == 36;
            7214083635
            1695452385
            5773159633
            1540955065
            8294398571
            1988161715
            9878712108
            8496433585
        SELECT city FROM airports
        WHERE id == 4;
            London


    1.THE THIEF'S LICENSE PLATE NUMBER, BANK ACCOUNT NUMBER, PHONE NUMBER AND PASSPORT NUMBER HAVE BEEN FOUND.
    ON FINDING THE PERSON ID USING THE ABOVE FOUND DATA, THE THIEF'S NAME CAN BE REVEALED.

    2.ON FINDING THE THIEF'S IDENTITY, THE ACCOMPLICE'S NAME CAN ALSO BE FOUND USING THE ACCOMPLICE'S RECIEVER PHONE ID.

    3.IT HAS ALREADY BEEN DISCOVERED THAT THE THIEF HAS ESCAPED TO LONDON BY INFERING FROM RAYMOND'S STATEMENT.
*/