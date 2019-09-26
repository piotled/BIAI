using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Model
{
	/// <summary>
	/// Digit object
	/// </summary>
	public class Digit
	{
		/// <summary>
		/// Stores pixel values as float from 0 to 1
		/// </summary>
		float[] pixelValues = new float[DigitSet.DIGIT_SIZE * DigitSet.DIGIT_SIZE];
		/// <summary>
		/// Stores pixels as bytes
		/// </summary>
		private byte[] pixels;
		/// <summary>
		/// Digit label
		/// </summary>
		private byte label;

		/// <summary>
		/// Creates digit float representation
		/// </summary>
		/// <param name="pixels">Byte pixel value array</param>
		/// <param name="label">Label</param>
		public Digit(byte[] pixels, byte label)
		{
			this.pixels = pixels;
			this.label = label;
			ConvertPixelValuesToFloat();
		}

		/// <summary>
		/// Digit label
		/// </summary>
		public byte Label
		{
			get
			{
				return label;
			}
		}

		/// <summary>
		/// Digit pixels in form of float list
		/// </summary>
		public List<float> DigitPixels
		{
			get
			{
				return new List<float>(pixelValues);
			}
		}

		/// <summary>
		/// Converts byte array of pixel values to float list 
		/// </summary>
		private void ConvertPixelValuesToFloat()
		{
			for(int i = 0; i < pixels.Length; i++)
			{
				pixelValues[i] = pixels[i] / (float)byte.MaxValue;
			}
		}
	}
}
