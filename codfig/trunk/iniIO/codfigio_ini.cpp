#include "codfigio_ini.h"

using codfig::ConfigIOini;
using codfig::Config;

Config ConfigIOini::getConfig() {
	return Config(ApplicationID("Test App", "0.0.0", "Shaun Bouckaert"));
}

void ConfigIOini::saveConfig(const Config & theConfig) {
}