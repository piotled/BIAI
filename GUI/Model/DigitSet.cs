using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Model
{
	/// <summary>
	/// Contains digits loaded from files
	/// </summary>
	public class DigitSet : IDisposable
	{
		public const uint DIGIT_SIZE = 28;
		private FileStream digitFileStream;
		private FileStream labelFileStream;
		private Digit[] digits;
		uint count;

		/// <summary>
		/// Size of digit set. 
		/// </summary>
		public uint Size
		{
			get
			{
				return count;
			}
		}

		/// <summary>
		/// Opens and validates files
		/// </summary>
		/// <param name="digitFilePath"></param>
		/// <param name="labelFilePath"></param>
		public void Load(string digitFilePath, string labelFilePath)
		{
			Dispose();
			digitFileStream = new FileStream(digitFilePath, FileMode.Open);
			labelFileStream = new FileStream(labelFilePath, FileMode.Open);
			ValidateFileHeaders();
			LoadDigits();
		}

		/// <summary>
		/// Loads digits
		/// </summary>
		private void LoadDigits()
		{
			for (uint i = 0; i < count; i++)
			{
				digits[i] = LoadDigit();
			}
		}

		/// <summary>
		/// Reads digit from files
		/// </summary>
		/// <returns>Read digit</returns>
		private Digit LoadDigit()
		{
			byte[] pixels = new byte[DIGIT_SIZE * DIGIT_SIZE];
			digitFileStream.Read(pixels, 0, (int)(DIGIT_SIZE * DIGIT_SIZE));
			byte label = (byte)labelFileStream.ReadByte();
			return new Digit(pixels, label);
		}

		/// <summary>
		/// Checks file headers to prevent reading from files with incorrect format
		/// </summary>
		private void ValidateFileHeaders()
		{
			uint digitCount, labelCount;
			if (!ValidateDigitFileHeader(out digitCount))
			{
				throw new Exception("Incorrect digit file format");
			}
			else if (!ValidateLabelFileFormat(out labelCount))
			{
				throw new Exception("Incorrect label file format");
			}
			if(digitCount != labelCount)
			{
				throw new Exception("Digit and label files contents don't match");
			}
			else if(digitCount == 0)
			{
				throw new Exception("No digits to load");
			}
			count = digitCount;
			digits = new Digit[count];
		}

		/// <summary>
		/// Validates header in digit file
		/// </summary>
		/// <param name="digitCount">Variable to which digit count in file is saved</param>
		/// <returns>True if ok, false otherwise</returns>
		private bool ValidateDigitFileHeader(out uint digitCount)
		{
			const uint DIGCONF = 0x03080000;
			byte[] buffer32 = new byte[4];
			digitFileStream.Read(buffer32, 0, 4);
			if (BitConverter.ToUInt32(buffer32, 0) == DIGCONF)
			{
				digitFileStream.Read(buffer32, 0, 4);
				Array.Reverse(buffer32);
				digitCount = BitConverter.ToUInt32(buffer32, 0);
				digitFileStream.Read(buffer32, 0, 4);
				Array.Reverse(buffer32);
				uint xSize = BitConverter.ToUInt32(buffer32, 0);
				digitFileStream.Read(buffer32, 0, 4);
				Array.Reverse(buffer32);
				if (xSize == BitConverter.ToUInt32(buffer32, 0))
				{
					return true;
				}
			}
			digitCount = 0;
			return false;
		}

		/// <summary>
		/// Validates header in label file
		/// </summary>
		/// <param name="labelCount">Variable to which label count in file is saved</param>
		/// <returns>True if ok, false otherwise</returns>
		private bool ValidateLabelFileFormat(out uint labelCount)
		{
			const uint LABCONF = 0x01080000;
			byte[] buffer32 = new byte[4];
			labelFileStream.Read(buffer32, 0, 4);
			if (BitConverter.ToUInt32(buffer32, 0) == LABCONF)
			{
				labelFileStream.Read(buffer32, 0, 4);
				Array.Reverse(buffer32);
				labelCount = BitConverter.ToUInt32(buffer32, 0);
				return true;
			}
			labelCount = 0;
			return false;
		}

		/// <summary>
		/// Indexer
		/// </summary>
		/// <param name="index"></param>
		/// <returns>Digit at specified index</returns>
		public Digit this[uint index]
		{
			get
			{
				return digits[index];
			}
		}

		/// <summary>
		/// Closes file streams and resets indexes
		/// </summary>
		public void Dispose()
		{
			count = 0;
			digits = null;
			digitFileStream?.Close();
			labelFileStream?.Close();
		}
	}
}
