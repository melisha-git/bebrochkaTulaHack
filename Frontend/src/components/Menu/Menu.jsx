import Link from 'next/link'
import { BiUser, BiSearch, BiCalendarEvent } from 'react-icons/bi'
import { useDispatch } from 'react-redux'

import { setPage } from '@/store/slice/countSlice'

export default function Menu() {
	const dispatch = useDispatch()

	return (
		<div className='bg-white flex justify-center gap-12 py-4'>
			<button
				onClick={() => dispatch(setPage(3))}
				className=' text-2xl w-[50px] h-[50px] bg-black text-white rounded'
			>
				<BiUser className='m-auto' />
			</button>
			<Link href='/place'>
				<button
					onClick={() => dispatch(setPage(4))}
					className=' text-2xl w-[50px] h-[50px] bg-black text-white rounded'
				>
					<BiSearch className='m-auto' />
				</button>
			</Link>
			<button
				onClick={() => dispatch(setPage(5))}
				className='text-2xl w-[50px] h-[50px] bg-black text-white rounded'
			>
				<BiCalendarEvent className='m-auto' />
			</button>
		</div>
	)
}
