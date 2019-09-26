using GUI.Model;
using GUI.Networks;
using System;
using System.Collections.Generic;

namespace GUI.Controller
{
	/// <summary>
	/// Program controller. Manages network
	/// </summary>
	public class AppController
	{
		private Perceptron perceptron;
		private DigitSet digitSet = new DigitSet();
		private GUIForm mainForm;

		/// <summary>
		/// Size of digit set (0 if set not loaded)
		/// </summary>
		public uint DigitSetSize
		{
			get
			{
				return digitSet.Size;
			}
		}

		/// <summary>
		/// Saves main form reference
		/// </summary>
		/// <param name="mainForm">Form reference</param>
		public AppController(GUIForm mainForm)
		{
			this.mainForm = mainForm;
		}

		/// <summary>
		/// Access to last error message
		/// </summary>
		public string LastErrorMessage { get; private set; }

		/// <summary>
		/// Loads network from specified file
		/// </summary>
		/// <param name="filePath">Path to network file</param>
		/// <returns>true if loaded, false otherwise</returns>
		public bool LoadNetwork(string filePath)
		{
			try
			{
				perceptron = new Perceptron(filePath);
				return true;
			}
			catch(Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		/// <summary>
		/// Creates network in memory with provided format
		/// </summary>
		/// <param name="networkFormat">Network format</param>
		/// <returns>True if created, false otherwise</returns>
		public bool CreateNetwork(uint[] networkFormat)
		{
			try
			{
				perceptron = new Perceptron(new List<uint>(networkFormat));
				return true;
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		/// <summary>
		/// Save network to provided file
		/// </summary>
		/// <param name="filePath">Path of file to which network will be saved</param>
		/// <returns>true if saved, false otherwise</returns>
		public bool SaveNetwork(string filePath)
		{
			try
			{
				perceptron.Save(filePath);
				return true;
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		/// <summary>
		/// Load digit set from provided digit and label files
		/// </summary>
		/// <param name="digitFilePath"></param>
		/// <param name="labelFilePath"></param>
		/// <returns>true if loaded, false otherwise</returns>
		public bool LoadDigitSet(string digitFilePath, string labelFilePath)
		{
			try
			{
				digitSet.Load(digitFilePath, labelFilePath);
				return true;
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		/// <summary>
		/// Returns string with network structure desription
		/// </summary>
		/// <returns></returns>
		public string NetworkDescription()
		{
			return perceptron.Description;
		}

		/// <summary>
		/// Train network 
		/// </summary>
		/// <param name="startingIndex">Strating index in digit set</param>
		/// <param name="endingIndex">Ending index in digit set</param>
		/// <param name="learnRate"></param>
		/// <returns>true if all correct, false on errors</returns>
		public bool TrainNetwork(uint startingIndex, uint endingIndex, float learnRate)
		{
			try
			{
				if(perceptron != null)
				{
					if (digitSet.Size != 0)
					{
						if (endingIndex < digitSet.Size)
						{
							float totalError = 0;
							Trainer trainer = new Trainer(perceptron, learnRate);
							for(uint i = startingIndex; i <= endingIndex; i++)
							{
								TrainingResult result = trainer.Train(digitSet[i]);
								mainForm.ShowIteration(i);
								totalError += result.MeanSquareError;
							}
							totalError /= (endingIndex - startingIndex);
							mainForm.ShowTotalError(totalError);
							return true;
						}
						else
						{
							throw new Exception("Ending index exceeds digit set size");
						}
					}
					else
					{
						throw new Exception("Load digit set");
					}
				}
				else
				{
					throw new Exception("Load or create network");
				}
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		public void ClearNetwork()
		{
			perceptron = null;
		}

		/// <summary>
		/// Test network with digit set
		/// </summary>
		/// <param name="startingIndex">Starting index in digit set</param>
		/// <param name="endingIndex">Ending index in digit set</param>
		/// <returns>True if ok, false on errors</returns>
		public bool TestNetwork(uint startingIndex, uint endingIndex)
		{
			try
			{
				if (perceptron != null)
				{
					if (digitSet.Size != 0)
					{
						if (endingIndex < digitSet.Size)
						{
							uint correctCount = 0, incorrectCount = 0;
							Tester tester = new Tester(perceptron);
							for(uint i = startingIndex; i <= endingIndex; i++)
							{
								TestResult result = tester.Test(digitSet[i]);
								mainForm.ShowTestIteration(i);
								if (result.Correct)
								{
									correctCount++;
								}
								else
								{
									incorrectCount++;
								}
							}
							mainForm.ShowFileTestResults(correctCount, incorrectCount);
							return true;
						}
						else
						{
							throw new Exception("Ending index exceeds digit set size");
						}
					}
					else
					{
						throw new Exception("Load digit set");
					}
				}
				else
				{
					throw new Exception("Load or create network");
				}
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return false;
			}
		}

		/// <summary>
		/// Test network with single digit
		/// </summary>
		/// <param name="digitPixels">Digit as pixel values in float</param>
		/// <returns>Object containing test result</returns>
		public TestResult TestSingle(List<float> digitPixels)
		{
			try
			{
				if (perceptron != null)
				{
					Tester tester = new Tester(perceptron);
					return tester.Test(digitPixels);
				}
				else
				{
					throw new Exception("Load or create network");
				}
			}
			catch (Exception exc)
			{
				LastErrorMessage = exc.Message;
				return null;
			}
		}
	}
}