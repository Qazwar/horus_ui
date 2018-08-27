#include "types.h"
#include "horus.h"
#include "ui_context.h"
#include "util.h"
#include "3rdparty/nativefiledialog/src/include/nfd.h"
#include <string.h>

namespace hui
{
bool openFileDialog(const char* filterList, const char* defaultPath, char* outPath, u32 maxOutPathSize)
{
	char* path = 0;
	auto res = NFD_OpenDialog(filterList, defaultPath, &path);

	clearInputEventQueue();
	memcpy(outPath, path, std::min((int)maxOutPathSize, (int)strlen(path) + 1));
	delete [] path;

	if (res == NFD_ERROR || res == NFD_CANCEL)
		return false;

	return true;
}

bool openMultipleFileDialog(const char* filterList, const char* defaultPath, OpenMultipleFileSet& outPathSet)
{
	nfdpathset_t outPaths;
	auto res = NFD_OpenDialogMultiple(filterList, defaultPath, &outPaths);

	clearInputEventQueue();

	if (res == NFD_ERROR || res == NFD_CANCEL)
		return false;

	outPathSet.filenameBuffer = outPaths.buf;
	outPathSet.count = outPaths.count;
	outPathSet.bufferIndices = outPaths.indices;

	return true;
}

void destroyMultipleFileSet(OpenMultipleFileSet& fileSet)
{
	delete[]fileSet.filenameBuffer;
	delete[]fileSet.bufferIndices;
	fileSet.count = 0;
	fileSet.filenameBuffer = nullptr;
	fileSet.bufferIndices = nullptr;
}

bool saveFileDialog(const char* filterList, const char* defaultPath, char* outPath, u32 maxOutPathSize)
{
	char* path = 0;
	auto res = NFD_SaveDialog(filterList, defaultPath, &path);

	clearInputEventQueue();
	memcpy(outPath, path, std::min((int)maxOutPathSize, (int)strlen(path) + 1));
	delete [] path;

	if (res == NFD_ERROR || res == NFD_CANCEL)
		return false;

	return true;
}

bool pickFolderDialog(const char* defaultPath, char* outPath, u32 maxOutPathSize)
{
    enableInput(false);
	char* path = 0;	
	auto res = NFD_PickFolder(defaultPath, &path);
	
	clearInputEventQueue();
    enableInput(true);
	memcpy(outPath, path, std::min((int)maxOutPathSize, (int)strlen(path) + 1));
	delete [] path;

	if (res == NFD_ERROR || res == NFD_CANCEL)
		return false;

	return true;
}

}
