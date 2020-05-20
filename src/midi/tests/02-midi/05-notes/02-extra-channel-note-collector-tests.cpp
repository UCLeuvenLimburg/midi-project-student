#ifdef TEST_BUILD
#define CATCH_CONFIG_PREFIX_ALL
#define TEST_CASE CATCH_TEST_CASE

#include "midi/midi.h"
#include "Catch.h"
#include <vector>

/*
    Year 19-20: These tests are optional

    These tests focus on some errors that can appear in MIDI files.
    You should be able to handle these cases gracefully.
*/

TEST_CASE("Invalid MIDI: channel starts with note off -> ignore note")
{
    std::vector<midi::NOTE> notes;
    midi::ChannelNoteCollector collector(midi::Channel(0), [&notes](const midi::NOTE& note) { notes.push_back(note); });

    collector.note_off(midi::Duration(100), midi::Channel(0), midi::NoteNumber(5), 100);

    CATCH_REQUIRE(notes.size() == 0);
}

TEST_CASE("Invalid MIDI: on - off - off -> ignore second off")
{
    std::vector<midi::NOTE> notes;
    midi::ChannelNoteCollector collector(midi::Channel(0), [&notes](const midi::NOTE& note) { notes.push_back(note); });

    collector.note_on(midi::Duration(100), midi::Channel(0), midi::NoteNumber(5), 112);
    collector.note_off(midi::Duration(100), midi::Channel(0), midi::NoteNumber(5), 112);
    collector.note_off(midi::Duration(100), midi::Channel(0), midi::NoteNumber(5), 112);

    CATCH_REQUIRE(notes.size() == 1);
    CATCH_CHECK(notes[0] == midi::NOTE(midi::NoteNumber(5), midi::Time(100), midi::Duration(100), 112, midi::Instrument(0)));
}

#endif
