/**
 * @file Timer.cpp
 * @brief Implementarea clasei Timer pentru gestionarea temporizărilor în jocul Tetris.
 *
 * Clasa Timer este utilizată pentru a urmări intervalele de timp și pentru a verifica
 * dacă un anumit prag temporal a fost atins.
 */

#include "Timer.h"

using namespace TetrisAPI;

/**
 * @brief Constructorul clasei Timer.
 *
 * Inițializează un timer cu durata specificată în milisecunde.
 *
 * @param durationInMilliseconds Durata temporizării în milisecunde.
 */
Timer::Timer(const uint16_t& durationInMilliseconds) :
	m_duration{ milliseconds(durationInMilliseconds) },
	m_isActive{ false }
{
}

/**
 * @brief Returnează timpul scurs de la pornirea temporizării.
 *
 * @return milliseconds Timpul scurs în milisecunde.
 */
milliseconds Timer::GetElapsedTime() const
{
	auto currentTime{ high_resolution_clock::now() };
	return duration_cast<milliseconds>(currentTime - m_startTime);
}

/**
 * @brief Verifică dacă timpul scurs a atins sau a depășit durata specificată.
 *
 * @return true dacă timpul scurs a atins pragul, false în caz contrar.
 */
bool Timer::ReachedThreshold() const
{
	return GetElapsedTime() >= m_duration;
}

/**
 * @brief Pornește temporizarea.
 *
 * Stabilește momentul de început al temporizării la timpul curent și activează timerul.
 */
void Timer::Start()
{
	m_startTime = high_resolution_clock::now();
	m_isActive = true;
}

/**
 * @brief Oprește temporizarea.
 *
 * Dezactivează timerul fără a reseta timpul de început.
 */
void Timer::Stop()
{
	m_isActive = false;
}
