#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include "tooltype.h"
#include "diagramelement.h"
#include "blockdiagramelement.h"
#include "arrowdiagramelement.h"

#include <memory>
#include <sstream>

//extern BlockDiagramElement block;

struct Tool
{
    Tool(ToolType type) : type(type) {}

    ToolType type = ToolType::NO_TOOL;

    std::unique_ptr<DiagramElement> getDiagramElement() const noexcept
    {
        // return the Singleton object representing the ToolType of the calling Tool object
        switch (type) {
        case BLOCK: return std::make_unique<BlockDiagramElement>();
        case ARROW: return std::make_unique<ArrowDiagramElement>();
        default:
            std::ostringstream info("No such tool exists.", std::ios_base::ate);
            info << " Type: " << type << '.';
            throw std::invalid_argument(info.str());
        }

    }
};

#endif // ABSTRACTTOOL_H
