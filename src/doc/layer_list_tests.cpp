// Aseprite Document Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtest/gtest.h>

#include "base/unique_ptr.h"
#include "doc/layer.h"
#include "doc/layer_list.h"
#include "doc/sprite.h"

#include <algorithm>

using namespace doc;

TEST(LayerList, AreLayersAdjacent)
{
  base::UniquePtr<Sprite> spr(new Sprite(IMAGE_RGB, 32, 32, 256));
  LayerGroup* root = spr->root();
  Layer* layer1 = new LayerImage(spr);
  Layer* layer2 = new LayerImage(spr);
  Layer* layer3 = new LayerImage(spr);
  Layer* layer4 = new LayerImage(spr);
  root->addLayer(layer1);
  root->addLayer(layer2);
  root->addLayer(layer3);
  root->addLayer(layer4);

  LayerList layers;
  root->allLayers(layers);
  EXPECT_EQ(4, layers.size());
  EXPECT_TRUE(are_layers_adjacent(layers));

  std::reverse(layers.begin(), layers.end());
  EXPECT_EQ(4, layers.size());
  EXPECT_TRUE(are_layers_adjacent(layers));

  layers.erase(layers.begin());
  EXPECT_EQ(3, layers.size());
  EXPECT_TRUE(are_layers_adjacent(layers));

  layers.erase(layers.begin()+1);
  EXPECT_EQ(2, layers.size());
  EXPECT_FALSE(are_layers_adjacent(layers));

  std::reverse(layers.begin(), layers.end());
  EXPECT_EQ(2, layers.size());
  EXPECT_FALSE(are_layers_adjacent(layers));

  layers.erase(layers.begin());
  EXPECT_EQ(1, layers.size());
  EXPECT_TRUE(are_layers_adjacent(layers));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}