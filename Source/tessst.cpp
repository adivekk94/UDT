//#include <iostream>
//#include "tessst.hpp"
//#include "source/generator/SineGenerator.h"
//#include "tools/TextPlot.h"
//
//int main()
//{
//	Aquila::SineGenerator sine(10000);
//	sine.setFrequency(500).setAmplitude(20).generate(50000);
//	Aquila::TextPlot plot("Sine");
//	plot.plot(sine);
//	Aquila::SoundBufferAdapter buffer(sine);
////	if (!buffer.loadFromFile("/home/adivek/workspace/Licencjat/Source/choir.wav"))
////	{
////		cout << "Error with loading buffer file!" << endl;
////		return -1;
////	}
////	buffer.loadFromSignalSource(sine);
//
//	sf::Time t = buffer.getDuration();
//	cout << "Duration: " << buffer.getDuration().asSeconds() << endl;
//	sf::Sound sound(buffer);
//	sound.play();
//
//	sf::sleep(t);
//
//	return 0;
//}

/**
 * Playing the Imperial March from Star Wars.
 *
 * Notes and timings found at:
 *    http://processors.wiki.ti.com/index.php/Playing_The_Imperial_March
 */

#include "source/generator/SineGenerator.h"
#include "wrappers/SoundBufferAdapter.h"
#include <SFML/Audio.hpp>
#include <iostream>

/**
 * A beepy-beep thingy.
 */
class Beeper
{
public:
    Beeper(Aquila::FrequencyType sampleFrequency):
        SAMPLE_FREQUENCY(sampleFrequency), generator(SAMPLE_FREQUENCY)
    {
        generator.setAmplitude(8192);
    }

    /**
     * Makes a beep.
     *
     * @param note frequency of the generated sound
     * @param duration beep duration in milliseconds
     */
    void beep(unsigned int note, unsigned int duration)
    {
        unsigned int numSamples = SAMPLE_FREQUENCY * duration / 1000;
        generator.setFrequency(note).generate(numSamples);
        buffer.loadFromSignalSource(generator);
        sf::Sound sound(buffer);
        sound.play();

        sf::Time t = buffer.getDuration();

        // the additional 50 ms is an intentional pause between beeps
        sf::sleep(t);
    }

    /**
     * Waits for some time.
     *
     * @param duration delay time in milliseconds
     */
//    void delay(unsigned int duration)
//    {
//        sf::sleep(duration / 1000.0f);
//    }

private:
    const Aquila::FrequencyType SAMPLE_FREQUENCY;
    Aquila::SineGenerator generator;
    Aquila::SoundBufferAdapter buffer;
};


#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880


//int main(int argc, char** argv)
//{
//    std::cout << " The Imperial March (Darth Vader's Theme) \n\n"
//                 " composed by John Williams \n"
//                 " played by SFML, Aquila and... your speakers! \n\n"
//                 " Aquila DSP library: \n"
//                 " \t http://aquila-dsp.org \n\n"
//                 " SFML multimedia library: \n"
//                 " \t http://www.sfml-dev.org \n\n"
//                 " Notes and timings found at: \n"
//                 " \t http://processors.wiki.ti.com/index.php/Playing_The_Imperial_March \n\n"
//                 " (c) Zbigniew Siciarz 2010 \n" << std::endl;
//
//    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
//    Beeper beeper(SAMPLE_FREQUENCY);
//
//    beeper.beep(a, 500);
//    beeper.beep(a, 500);
//    beeper.beep(a, 500);
//    beeper.beep(f, 350);
//    beeper.beep(cH, 150);
//    beeper.beep(a, 500);
//    beeper.beep(f, 350);
//    beeper.beep(cH, 150);
//    beeper.beep(a, 650);
//
////    beeper.delay(150);
//
//    beeper.beep(eH, 500);
//    beeper.beep(eH, 500);
//    beeper.beep(eH, 500);
//    beeper.beep(fH, 350);
//    beeper.beep(cH, 150);
//    beeper.beep(gS, 500);
//    beeper.beep(f, 350);
//    beeper.beep(cH, 150);
//    beeper.beep(a, 650);
//
////    beeper.delay(150);
//
//    beeper.beep(aH, 500);
//    beeper.beep(a, 300);
//    beeper.beep(a, 150);
//    beeper.beep(aH, 400);
//    beeper.beep(gSH, 200);
//    beeper.beep(gH, 200);
//    beeper.beep(fSH, 125);
//    beeper.beep(fH, 125);
//    beeper.beep(fSH, 250);
//
////    beeper.delay(250);
//
//    beeper.beep(aS, 250);
//    beeper.beep(dSH, 400);
//    beeper.beep(dH, 200);
//    beeper.beep(cSH, 200);
//    beeper.beep(cH, 125);
//    beeper.beep(b, 125);
//    beeper.beep(cH, 250);
////
////    beeper.delay(250);
//
//    beeper.beep(f, 125);
//    beeper.beep(gS, 500);
//    beeper.beep(f, 375);
//    beeper.beep(a, 125);
//    beeper.beep(cH, 500);
//    beeper.beep(a, 375);
//    beeper.beep(cH, 125);
//    beeper.beep(eH, 650);
//
//    beeper.beep(aH, 500);
//    beeper.beep(a, 300);
//    beeper.beep(a, 150);
//    beeper.beep(aH, 400);
//    beeper.beep(gSH, 200);
//    beeper.beep(gH, 200);
//    beeper.beep(fSH, 125);
//    beeper.beep(fH, 125);
//    beeper.beep(fSH, 250);
//
////    beeper.delay(250);
//
//    beeper.beep(aS, 250);
//    beeper.beep(dSH, 400);
//    beeper.beep(dH, 200);
//    beeper.beep(cSH, 200);
//    beeper.beep(cH, 125);
//    beeper.beep(b, 125);
//    beeper.beep(cH, 250);
//
////    beeper.delay(250);
//
//    beeper.beep(f, 250);
//    beeper.beep(gS, 500);
//    beeper.beep(f, 375);
//    beeper.beep(cH, 125);
//    beeper.beep(a, 500);
//    beeper.beep(f, 375);
//    beeper.beep(cH, 125);
//    beeper.beep(a, 650);
//
//    return 0;
//}
