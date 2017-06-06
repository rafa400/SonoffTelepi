#!/bin/bash
#
function minimiza { 
export TELEPI=$(html-minifier --collapse-whitespace --html5 --remove-comments --remove-redundant-attributes --remove-tag-whitespace --sort-attributes --sort-class-name --trim-custom-fragments --use-short-doctype $1)
}

echo "#ifndef TELEPIHTML_H"
echo "#define TELEPIHTML_H"
echo 'const char purecss[] PROGMEM = R"=====('"`cat "pure-release-0.6.2/pure-min.css"`"')=====";'
echo 'const char jsuijs[] PROGMEM = R"=====('"`cat "js/ui.js"`"')=====";'
echo 'const char sidemenucss[] PROGMEM = R"=====('"`cat "css/layouts/side-menu.css"`"')=====";'
echo 'const char buttoncss[] PROGMEM = R"=====('"`cat "css/button.css"`"')=====";'
echo 'const char sonoffsvgchar[] PROGMEM = R"=====('"`cat "sonoff.svg"`"')=====";'

echo 'const char indexhtml[] PROGMEM = R"=====('"`cat index.html`"')=====";'
echo 'const char wifisetuphtml[] PROGMEM = R"=====('"`cat wifisetup.html`"')=====";'
echo 'const char workmodehtml[] PROGMEM = R"=====('"`cat workmode.html`"')=====";'
echo 'const char linkwithhtml[] PROGMEM = R"=====('"`cat linkwith.html`"')=====";'
echo 'const char mqtthtml[] PROGMEM = R"=====('"`cat mqtt.html`"')=====";'
echo 'const char updatehtml[] PROGMEM = R"=====('"`cat update.html`"')=====";'

echo "#endif //TELEPIHTML_H"
exit 0
