import Image from 'next/image'
import { BiMap, BiTime, BiMale } from 'react-icons/bi'

export default function CalendarItem({ data }) {
	return (
		<div className='flex items-center mb-2 border p-2 rounded-md'>
			<div className=' relative w-24 h-24 rounded mr-2'>
				<Image src={data.place_image} fill className=' rounded' />
			</div>
			<div>
				<div className=' text-xl font-medium'>{data.place_name}</div>
				<div className='flex items-center'>
					<BiMap className=' mr-1' />
					<div>{data.place_adress}</div>
				</div>
				<div className='flex  items-center'>
					<BiMale className=' mr-1' />
					{data.friend}
				</div>
				<div className='flex  items-center'>
					<BiTime className=' mr-1' />
					<div className='mr-2'>{data.date}</div>
					<div>{data.time}</div>
				</div>
			</div>
		</div>
	)
}
