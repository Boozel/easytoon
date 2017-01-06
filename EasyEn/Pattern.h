#define PATTERN_SIZE 8

class Pattern
{
private:
	static CBitmap *_pattern;
	static CBitmap *_patterns;
	static CBitmap *_patternsMenu;
	
	static bool _isInitialized;
	static int _rowsNumber;
	static int _colsNumber;
	static int _rowPos;

public:
	Pattern();
	Pattern::~Pattern();
	static void InitializePattern(int resourceId);
	static void PreviousPattern();
	static void NextPattern();
	static CBitmap* GetPatternForMenu();
	static CBitmap* GetPattern(int patternCol);
	

};