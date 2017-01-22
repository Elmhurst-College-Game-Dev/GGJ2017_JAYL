#pragma once

class TextureDescriber {
public:
	explicit TextureDescriber(const char *jsonFile, const char *textureFile);

private:
	const char *jsonFile;
	const char *textureFile;

};