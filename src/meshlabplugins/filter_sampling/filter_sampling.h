/****************************************************************************
* MeshLab                                                           o o     *
* A versatile mesh processing toolbox                             o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
#ifndef FILTERDOCSAMPLINGPLUGIN_H
#define FILTERDOCSAMPLINGPLUGIN_H

#include <common/interfaces.h>

class FilterDocSampling : public QObject, public MeshFilterInterface
{
  Q_OBJECT
  MESHLAB_PLUGIN_IID_EXPORTER(MESH_FILTER_INTERFACE_IID)
  Q_INTERFACES(MeshFilterInterface)

  public:
    enum {
    FP_ELEMENT_SUBSAMPLING,
        FP_MONTECARLO_SAMPLING,
        FP_REGULAR_RECURSIVE_SAMPLING,
        FP_CLUSTERED_SAMPLING,
        FP_STRATIFIED_SAMPLING,
        FP_HAUSDORFF_DISTANCE,
		FP_DISTANCE_REFERENCE,
        FP_TEXEL_SAMPLING,
        FP_VERTEX_RESAMPLING,
        FP_UNIFORM_MESH_RESAMPLING,
        FP_VORONOI_COLORING,
        FP_DISK_COLORING,
        FP_POISSONDISK_SAMPLING,
        FP_POINTCLOUD_SIMPLIFICATION
  } ;

  FilterDocSampling();

  QString filterName(FilterIDType filter) const;
  QString filterInfo(FilterIDType filter) const;
  void initParameterSet(QAction *,MeshDocument &/*m*/, RichParameterSet & /*parent*/);
  bool applyFilter(QAction *filter, MeshDocument &m, RichParameterSet & /*parent*/, vcg::CallBackPos * cb) ;
  int getRequirements(QAction *action);
  int postCondition( QAction* ) const;
  FilterClass getClass(QAction *);
  FILTER_ARITY filterArity(QAction * filter) const;
};

#endif
