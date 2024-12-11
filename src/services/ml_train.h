// Copyright 2024 Robert Carneiro
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and
// associated documentation files (the "Software"), to deal in the Software
// without restriction,
// including without limitation the rights to use, copy, modify, merge, publish,
// distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom
// the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef _ML_TRAIN
#define _ML_TRAIN

#include "../crt0.h"
#include "../main.h"
#include "Backend/Database/GList.h"
#include "Backend/Database/GTable.h"
#include "Backend/Database/ServiceData.h"
#include "Backend/Machine Learning/DataObjects/ImageInput.h"
#include "Backend/Machine Learning/DataObjects/NumberInput.h"
#include "Backend/Machine Learning/Networks/metanetwork.h"
#include "Backend/Machine Learning/Networks/network.h"
#include "Backend/Machine Learning/State/Terminator.h"
#include "Backend/Machine Learning/Structure/hiddenlayerinfo.h"
#include "Backend/Machine Learning/Structure/inputlayerinfo.h"
#include "Backend/Machine Learning/Structure/nninfo.h"
#include "Backend/Machine Learning/Structure/outputlayerinfo.h"
#include "Backend/Machine Learning/main.h"
#include "Backend/Networking/service.h"
#include "Frontend/GUI/RUMsgBox.h"
#include "Frontend/Graphics/graphics.h"

class NNInfo;

class ML_Train : public GNet::Service
{
private:
	GNet::GServer* serverInstance;
	glades::NNetwork cNetwork;

public:
	ML_Train()
	{
		serverInstance = NULL;
	}

	ML_Train(GNet::GServer* newInstance)
	{
		serverInstance = newInstance;
	}

	~ML_Train()
	{
		serverInstance = NULL; // Not ours to delete
	}

	shmea::ServiceData* execute(const shmea::ServiceData* data)
	{
		class GNet::Connection* destination = data->getConnection();

		if (data->getType() != shmea::ServiceData::TYPE_LIST)
			return NULL;

		shmea::GList cList = data->getList();

		if ((cList.size() == 1) && (cList.getString(0) == "KILL"))
		{
			if (!cNetwork.getRunning())
				return NULL;

			cNetwork.stop();
			printf("\n!!---KILLING NET---!!\n");
		}

		if (cList.size() < 3)
			return NULL;

		shmea::GString netName = cList.getString(0);
		shmea::GString inputFName = cList.getString(1);
		int inputType = cList.getInt(2);
		/*int64_t maxTimeStamp = cList.getLong(3);
		int64_t maxEpoch = cList.getLong(4);
		float maxAccuracy = cList.getFloat(5);*/
		// int64_t trainPct = cList.getLong(4), testPct = cList.getLong(5), validationPct =
		// cList.getLong(6);

		// Modify the paths to properly load the data later
		glades::DataInput* di = NULL;
		if (inputType == glades::DataInput::CSV)
		{
			inputFName = "datasets/" + inputFName;
			di = new glades::NumberInput();
		}
		else if (inputType == glades::DataInput::IMAGE)
		{
			// inputFName = "datasets/images/" + inputFName + "/";
			di = new glades::ImageInput();
		}
		else if (inputType == glades::DataInput::TEXT)
		{
			// TODO
			return NULL;
		}
		else
			return NULL;

		if (!di)
			return NULL;

		// Load the input data
		di->import(inputFName);

		// Load the neural network
		if ((cNetwork.getEpochs() == 0) && (!cNetwork.load(netName)))
		{
			printf("[NN] Unable to load \"%s\"", netName.c_str());
			return NULL;
		}

		// Termination Conditions
		/*cNetwork.terminator.setTimestamp(maxTimeStamp);
		cNetwork.terminator.setEpoch(maxEpoch);
		cNetwork.terminator.setAccuracy(maxAccuracy);*/

		// Run the training and retrieve a metanetwork
		glades::MetaNetwork* newTrainNet =
			glades::train(&cNetwork, di, serverInstance, destination);

		return NULL;
	}

	GNet::Service* MakeService(GNet::GServer* newInstance) const
	{
		return new ML_Train(newInstance);
	}

	shmea::GString getName() const
	{
		return "ML_Train";
	}
};

#endif
