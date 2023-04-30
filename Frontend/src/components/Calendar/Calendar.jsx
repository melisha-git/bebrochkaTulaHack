import { BiSmile } from 'react-icons/bi'

import { getByName } from '@/service/calendar.service'
import CalendarItem from './Item'

export default function Calendar() {
	const name = localStorage.getItem('name')
	const { data, isSuccess } = getByName(name)
	return (
		<div className=' max-h-96 overflow-y-scroll' id='placelist'>
			{isSuccess &&
				data.map((item, id) => <CalendarItem key={id} data={item} />)}
			{data?.length === 0 && (
				<div className='flex items-center justify-center'>
					Войдите или добавьте мероприятие
					<BiSmile className='ml-2' />
				</div>
			)}
		</div>
	)
}
