#pragma once

class UnCopyable
{
private:
	UnCopyable(const UnCopyable &uc);

	const UnCopyable& operator = (const UnCopyable &uc);

protected:
	UnCopyable() {}
};
