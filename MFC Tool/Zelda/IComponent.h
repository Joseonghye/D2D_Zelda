#pragma once

enum ComponetID{Collider,Animation};

__interface IComponet
{
public:
	IComponent();
	virtual ~IComponent() noexcept { __noop; }
};