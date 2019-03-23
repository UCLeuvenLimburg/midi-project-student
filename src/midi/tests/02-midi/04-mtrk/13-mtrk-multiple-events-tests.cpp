#ifdef TEST_BUILD
#define CATCH_CONFIG_PREFIX_ALL
#define TEST_CASE CATCH_TEST_CASE

#include "tests/tests-util.h"
#include <sstream>

using namespace testutils;


TEST_CASE("Reading MTrk, multiple note on events without running status")
{
    char buffer[] = {
        MTRK,
        0x00, 0x00, 0x00, 12, // Length
        0, NOTE_ON(0, 0, 0),
        10, NOTE_ON(0, 5, 0),
        END_OF_TRACK
    };
    std::string data(buffer, sizeof(buffer));
    std::stringstream ss(data);

    auto receiver = Builder()
        .note_on(midi::Duration(0), midi::Channel(0), midi::NoteNumber(0), 0)
        .note_on(midi::Duration(10), midi::Channel(0), midi::NoteNumber(5), 0)
        .meta(midi::Duration(0), 0x2F, "")
        .build();

    read_mtrk(ss, *receiver);
}

TEST_CASE("Reading MTrk, multiple note on events with running status")
{
    char buffer[] = {
        MTRK,
        0x00, 0x00, 0x00, 11, // Length
        0, NOTE_ON(0, 0, 0),
        10, NOTE_ON_RS(5, 0),
        END_OF_TRACK
    };
    std::string data(buffer, sizeof(buffer));
    std::stringstream ss(data);

    auto receiver = Builder()
        .note_on(midi::Duration(0), midi::Channel(0), midi::NoteNumber(0), 0)
        .note_on(midi::Duration(10), midi::Channel(0), midi::NoteNumber(5), 0)
        .meta(midi::Duration(0), 0x2F, "")
        .build();

    read_mtrk(ss, *receiver);
}

TEST_CASE("Reading MTrk, multiple note off events with running status")
{
    char buffer[] = {
        MTRK,
        0x00, 0x00, 0x00, 14, // Length
        0, NOTE_OFF(1, 0, 0),
        10, NOTE_OFF_RS(5, 0),
        20, NOTE_OFF_RS(9, 0),
        END_OF_TRACK
    };
    std::string data(buffer, sizeof(buffer));
    std::stringstream ss(data);

    auto receiver = Builder()
        .note_off(midi::Duration(0), midi::Channel(1), midi::NoteNumber(0), 0)
        .note_off(midi::Duration(10), midi::Channel(1), midi::NoteNumber(5), 0)
        .note_off(midi::Duration(20), midi::Channel(1), midi::NoteNumber(9), 0)
        .meta(midi::Duration(0), 0x2F, "")
        .build();

    read_mtrk(ss, *receiver);
}

TEST_CASE("Reading MTrk consisting of note on, note on, note off, note off")
{
    char buffer[] = {
        MTRK,
        0x00, 0x00, 0x00, 18, // Length
        0, NOTE_ON(0, 50, 127),
        0, NOTE_ON_RS(49, 127),
        10, NOTE_OFF(0, 50, 0),
        0, NOTE_OFF_RS(49, 0),
        END_OF_TRACK
    };
    std::string data(buffer, sizeof(buffer));
    std::stringstream ss(data);

    auto receiver = Builder()
        .note_on(midi::Duration(0), midi::Channel(0), midi::NoteNumber(50), 127)
        .note_on(midi::Duration(0), midi::Channel(0), midi::NoteNumber(49), 127)
        .note_off(midi::Duration(10), midi::Channel(0), midi::NoteNumber(50), 0)
        .note_off(midi::Duration(0), midi::Channel(0), midi::NoteNumber(49), 0)
        .meta(midi::Duration(0), 0x2F, "")
        .build();

    read_mtrk(ss, *receiver);
    receiver->check_finished();
}

#endif
