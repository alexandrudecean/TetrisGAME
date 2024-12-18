/**
 * @file Grid.cpp
 * @brief Implementarea clasei Grid care gestionează grila jocului Tetris.
 *
 * Clasa Grid gestionează plasarea blocurilor, mișcările acestora, rotațiile și ștergerea liniilor complete.
 */
#include "Grid.h"

using namespace TetrisAPI;

/**
 * @brief Constructorul clasei Grid.
 *
 * Inițializează grila jocului cu celule goale de o culoare specificată.
 *
 * @param emptyCellColor Culoarea utilizată pentru celulele goale din grilă.
 */
Grid::Grid(const Color& emptyCellColor) :
	m_emptyCellColor{ emptyCellColor },
	m_blockCanMove{ false }
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		std::vector<Color> line;
		for (size_t j = 0; j < WIDTH; j++)
		{
			line.emplace_back(m_emptyCellColor);
		}
		m_grid.emplace_back(line);
	}
}

/**
 * @brief Coboară blocul curent până la poziția maximă posibilă.
 */
void Grid::MoveDown()
{
	while (m_blockCanMove)
		Move(Position::Down);
}

/**
 * @brief Șterge liniile complete din grilă.
 *
 * @return uint16_t Numărul de linii șterse.
 */
uint16_t Grid::ClearFullLines()
{
	uint16_t linesCleared = 0;
	int16_t fullLine = GetFullLine();
	while (fullLine != -1)
	{
		linesCleared++;
		ClearLine(fullLine);
		fullLine = GetFullLine();
	}
	return linesCleared;
}

/**
 * @brief Rotește blocul curent.
 *
 * @return true dacă rotația a fost efectuată cu succes, false în caz contrar.
 */
bool Grid::Rotate()
{
	if (!m_blockCanMove)
		return false;

	RemoveCurrentBlock();
	m_currentBlock->Rotate();
	if (TrySpawnCurrentBlock(m_currentBlockOffset))
	{
		SpawnCurrentBlock();
		return true;
	}
	m_currentBlock->UndoRotate();
	SpawnCurrentBlock();
	return false;
}

/**
 * @brief Mută blocul curent în direcția specificată.
 *
 * @param pos Direcția în care să fie mutat blocul.
 */
void Grid::Move(const Position& pos)
{
	Position newOffset = m_currentBlockOffset + pos;
	RemoveCurrentBlock();
	if (TrySpawnCurrentBlock(newOffset))
	{
		m_currentBlockOffset = newOffset;
		SpawnCurrentBlock();
		return;
	}

	if (pos == Position::Down)
		m_blockCanMove = false;
	
	SpawnCurrentBlock();
}

/**
 * @brief Plasează un bloc nou în grilă.
 *
 * @param block Blocul care trebuie plasat.
 * @return true dacă blocul a fost plasat cu succes, false dacă nu există spațiu.
 */
bool Grid::SpawnBlock(const Block& block)
{
	m_currentBlock = block;
	m_currentBlockOffset = { WIDTH / 2, 0 };
	m_blockCanMove = true;

	if (!TrySpawnCurrentBlock(m_currentBlockOffset))
		return false;

	SpawnCurrentBlock();
	return true;
}

/**
 * @brief Găsește prima linie completă din grilă.
 *
 * @return int16_t Indexul liniei complete sau -1 dacă nu există linii complete.
 */
int16_t Grid::GetFullLine() const
{
	for (int16_t lineIndex = HEIGHT - 1; lineIndex >= 0; lineIndex--)
	{
		if (LineIsFull(lineIndex))
			return lineIndex;
	}
	return -1;
}

/**
 * @brief Verifică dacă o linie este completă.
 *
 * @param line Indexul liniei care trebuie verificată.
 * @return true dacă linia este completă, false în caz contrar.
 */
bool Grid::LineIsFull(size_t line) const
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		if (IsPositionEmpty(Position(i, line)))
			return false;
	}
	return true;
}

/**
 * @brief Șterge o linie completă și mută liniile de deasupra în jos.
 *
 * @param line Indexul liniei care trebuie ștearsă.
 */
void Grid::ClearLine(size_t line)
{
	for (size_t i = line; i > 0; i--)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			m_grid[i][j] = m_grid[i - 1][j];
		}
	}
	for (size_t j = 0; j < WIDTH; j++)
	{
		m_grid[0][j] = m_emptyCellColor;
	}
}

/**
 * @brief Verifică dacă blocul curent poate fi plasat la un anumit offset.
 *
 * @param offset Poziția offsetului pentru plasarea blocului.
 * @return true dacă blocul poate fi plasat, false în caz contrar.
 */
bool Grid::TrySpawnCurrentBlock(const Position& offset) const
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		Position position = pos + offset;
		if (!TrySpawnAt(position))
			return false;
	}
	return true;
}

/**
 * @brief Verifică dacă o poziție poate fi utilizată pentru plasarea unui bloc.
 *
 * @param pos Poziția care trebuie verificată.
 * @return true dacă poziția este validă, false în caz contrar.
 */
bool Grid::TrySpawnAt(const Position& pos) const
{
	if (IsPositionInGrid(pos))
	{
		if (IsPositionEmpty(pos))
			return true;
		return false;
	}
	return false;
}

/**
 * @brief Setează celulele curente ale blocului la o anumită culoare.
 *
 * @param color Culoarea care trebuie setată pentru celulele blocului curent.
 */
void Grid::SetCurrentBlockCells(const Color& color)
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		(*this)[pos + m_currentBlockOffset] = color;
	}
}

/**
 * @brief Plasează blocul curent în grilă.
 */
void Grid::SpawnCurrentBlock()
{
	SetCurrentBlockCells(m_currentBlock->GetColor());
}

/**
 * @brief Elimină blocul curent din grilă.
 */
void Grid::RemoveCurrentBlock()
{
	SetCurrentBlockCells(m_emptyCellColor);
}

/**
 * @brief Verifică dacă o poziție din grilă este goală.
 *
 * @param pos Poziția care trebuie verificată.
 * @return true dacă poziția este goală, false în caz contrar.
 */
bool Grid::IsPositionEmpty(const Position& pos) const
{
	return (*this)[pos] == m_emptyCellColor;
}

/**
 * @brief Verifică dacă o poziție este în limitele grilei.
 *
 * @param pos Poziția care trebuie verificată.
 * @return true dacă poziția este în limitele grilei, false în caz contrar.
 */
bool Grid::IsPositionInGrid(const Position& pos) const
{
	return  pos.GetX() >= 0 && pos.GetX() < WIDTH &&
		pos.GetY() >= 0 && pos.GetY() < HEIGHT;
}

/**
 * @brief Operator de acces pentru o poziție din grilă.
 *
 * @param pos Poziția din grilă care trebuie accesată.
 * @return Color& Referință la culoarea din poziția specificată.
 */
Color& Grid::operator[](const Position& pos)
{
	return m_grid[pos.GetY()][pos.GetX()];
}

/**
 * @brief Operator de acces constant pentru o poziție din grilă.
 *
 * @param pos Poziția din grilă care trebuie accesată.
 * @return const Color& Referință constantă la culoarea din poziția specificată.
 */
const Color& Grid::operator[](const Position& pos) const
{
	return m_grid[pos.GetY()][pos.GetX()];
}
