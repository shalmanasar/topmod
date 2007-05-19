/* $Id: PatchRenderer.hh,v 1.1.1.1 2007/03/10 18:32:17 stuart Exp $ */

#ifndef _PATCH_RENDERER_HH_

#define _PATCH_RENDERER_HH_

/*
  PatchRenderer
  A renderer for DLFL objects, derived from DLFLRenderer
  Renders using Bezier patches
*/

#include "DLFLRenderer.hh"

class PatchRenderer;
typedef PatchRenderer * PatchRendererPtr;

class PatchRenderer : public DLFLRenderer
{
  public :

        /* Default constructor */
     PatchRenderer()
       : DLFLRenderer()
       {}

        /* Copy constructor */
     PatchRenderer(const PatchRenderer& nr)
       : DLFLRenderer(nr)
       {}

        /* Assignment operator */
     PatchRenderer& operator = (const PatchRenderer& nr)
       {
         DLFLRenderer::operator = (nr);
         return (*this);
       }

        /* Destructor */
     virtual ~PatchRenderer()
       {}

	/* Draw the overlays - different from regular renderers */
     virtual void drawOverlays(DLFLObjectPtr object) const
     {
       if ( DLFLRenderer::render_flags & ShowWireframe )
	  {
	    glColor3f(0.8,0.8,0.7);
	    glLineWidth(0.5);
	    glDepthRange(0.0,1.0-0.0005);
	    object->renderWireframePatches();
	  }
       if ( DLFLRenderer::render_flags & ShowSilhouette )
	  {
	    glColor3f(0.4,0.6,0.4);
	    glLineWidth(2.0);
	    glDepthRange(0.0,1.0-0.00055);
	    object->renderPatchBoundaries();

	    glColor3f(0.2,0.2,0.3);
	    glLineWidth(3.0);
	    glDepthRange(0.0,1.0-0.0006);
	    object->renderPatchFaceBoundaries();
	  }
       if ( DLFLRenderer::render_flags & ShowVertices )
	  {
               /*
	    glColor3f(0.2,0.2,0.3);
	    glLineWidth(3.0);
	    glDepthRange(0.0,1.0-0.0006);
	    object->renderPatchFaceBoundaries();
               */

            glColor3f(0.5,1.0,0.0);
	    glPointSize(5.0);
	    glDepthRange(0.0,1.0-0.00075);
	    object->renderPointPatches();

	  }
       if ( DLFLRenderer::render_flags & ShowNormals )
          {
            glColor3f(0.2,0.8,0.2);
            glLineWidth(1.0);
            object->renderPatchNormals();
          }
     }

        /* Implement render function */
     virtual int render(DLFLObjectPtr object) const
       {
         glEnable(GL_CULL_FACE);
         setCulling();
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	 glColor3f(0.3,0.5,0.8);
	 object->renderPatches();
	 drawOverlays(object);
	 glColor3f(0.5,0.2,0.2);
	 object->renderEdges(1.0);
	 object->renderPointPatches( );
         glDisable(GL_CULL_FACE);
         return 0;
       }
};

#endif /* #ifndef _PATCH_RENDERER_HH_ */

/*
  $Log: PatchRenderer.hh,v $
  Revision 1.1.1.1  2007/03/10 18:32:17  stuart
  Initial CVS Import

*/